---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-04 08:54:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 182 |
| Sample Rate | 3.03/sec |
| Health Score | 189% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 204 |
| Sample Rate | 3.40/sec |
| Health Score | 212% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 32-55 cores)</summary>

```
1793800157 32
1793800162 32
1793800167 32
1793800172 53
1793800177 53
1793800182 53
1793800187 53
1793800192 53
1793800197 53
1793800202 53
1793800207 53
1793800212 53
1793800217 53
1793800222 53
1793800227 53
1793800232 53
1793800237 53
1793800242 53
1793800247 53
1793800252 53
```
</details>

---

