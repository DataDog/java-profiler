---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-19 13:35:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 12 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (3 unique values: 31-36 cores)</summary>

```
1795112736 31
1795112741 31
1795112746 31
1795112751 31
1795112756 31
1795112761 31
1795112766 31
1795112771 31
1795112776 31
1795112781 31
1795112786 31
1795112791 31
1795112796 31
1795112802 31
1795112807 31
1795112812 31
1795112817 31
1795112822 31
1795112827 31
1795112832 31
```
</details>

---

