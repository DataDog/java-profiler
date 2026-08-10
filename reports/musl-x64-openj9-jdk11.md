---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-10 15:00:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 755 |
| Sample Rate | 12.58/sec |
| Health Score | 786% |
| Threads | 9 |
| Allocations | 546 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1786388113 48
1786388118 48
1786388123 48
1786388128 48
1786388133 48
1786388138 48
1786388143 43
1786388148 43
1786388153 43
1786388158 43
1786388163 43
1786388168 43
1786388173 43
1786388178 43
1786388183 43
1786388188 43
1786388193 43
1786388198 43
1786388203 43
1786388208 43
```
</details>

---

