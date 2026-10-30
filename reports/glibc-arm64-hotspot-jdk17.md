---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-30 07:23:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 21 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 8 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 12 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (2 unique values: 21-32 cores)</summary>

```
1793359139 21
1793359144 21
1793359149 21
1793359154 21
1793359159 21
1793359164 21
1793359169 21
1793359174 21
1793359179 21
1793359184 21
1793359189 21
1793359194 32
1793359199 32
1793359204 32
1793359209 32
1793359214 21
1793359219 21
1793359224 21
1793359229 21
1793359234 21
```
</details>

---

