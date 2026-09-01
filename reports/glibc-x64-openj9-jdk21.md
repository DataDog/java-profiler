---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-01 15:37:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 10 |
| Allocations | 344 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 572 |
| Sample Rate | 9.53/sec |
| Health Score | 596% |
| Threads | 11 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (2 unique values: 41-61 cores)</summary>

```
1788291118 61
1788291123 61
1788291128 61
1788291133 61
1788291138 61
1788291143 61
1788291148 61
1788291153 61
1788291158 61
1788291163 61
1788291168 61
1788291173 61
1788291178 61
1788291183 61
1788291188 41
1788291193 41
1788291198 41
1788291203 41
1788291208 41
1788291213 41
```
</details>

---

