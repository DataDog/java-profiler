---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 05:21:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
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
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 8 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1083 |
| Sample Rate | 18.05/sec |
| Health Score | 1128% |
| Threads | 10 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (3 unique values: 43-47 cores)</summary>

```
1794478532 47
1794478537 47
1794478542 47
1794478547 47
1794478552 47
1794478557 47
1794478562 47
1794478567 47
1794478572 47
1794478577 47
1794478582 47
1794478587 47
1794478592 47
1794478597 47
1794478603 47
1794478608 47
1794478613 47
1794478618 47
1794478623 45
1794478628 45
```
</details>

---

