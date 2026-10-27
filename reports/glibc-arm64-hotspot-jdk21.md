---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-27 07:43:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 565 |
| Sample Rate | 9.42/sec |
| Health Score | 589% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 13 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (3 unique values: 45-58 cores)</summary>

```
1793101167 47
1793101172 47
1793101177 47
1793101182 47
1793101187 47
1793101192 47
1793101197 47
1793101202 47
1793101207 47
1793101212 47
1793101217 47
1793101222 47
1793101227 47
1793101232 58
1793101237 58
1793101242 58
1793101247 58
1793101252 58
1793101257 45
1793101262 45
```
</details>

---

