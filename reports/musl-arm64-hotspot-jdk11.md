---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-29 08:52:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 269 |
| Sample Rate | 4.48/sec |
| Health Score | 280% |
| Threads | 11 |
| Allocations | 149 |

<details>
<summary>CPU Timeline (4 unique values: 39-44 cores)</summary>

```
1793278086 39
1793278091 39
1793278096 39
1793278101 39
1793278106 39
1793278111 44
1793278116 44
1793278121 44
1793278126 41
1793278131 41
1793278136 41
1793278141 41
1793278146 41
1793278151 41
1793278156 41
1793278161 41
1793278166 41
1793278171 41
1793278176 41
1793278181 41
```
</details>

---

