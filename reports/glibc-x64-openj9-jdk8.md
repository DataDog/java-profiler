---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-05-05 08:22:42 EDT

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 173 |
| Sample Rate | 2.88/sec |
| Health Score | 180% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 699 |
| Sample Rate | 11.65/sec |
| Health Score | 728% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 52-62 cores)</summary>

```
1777983477 52
1777983482 52
1777983487 52
1777983492 57
1777983497 57
1777983502 57
1777983507 57
1777983512 57
1777983517 57
1777983522 62
1777983527 62
1777983532 62
1777983537 62
1777983542 62
1777983547 62
1777983552 62
1777983557 62
1777983562 62
1777983567 62
1777983572 62
```
</details>

---

