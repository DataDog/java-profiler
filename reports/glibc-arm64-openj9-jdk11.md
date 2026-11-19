---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 13:28:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 124 |
| Sample Rate | 2.07/sec |
| Health Score | 129% |
| Threads | 8 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 118 |
| Sample Rate | 1.97/sec |
| Health Score | 123% |
| Threads | 9 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (2 unique values: 50-64 cores)</summary>

```
1795112613 50
1795112618 50
1795112623 50
1795112628 50
1795112633 50
1795112638 50
1795112643 50
1795112648 50
1795112653 50
1795112658 50
1795112663 50
1795112668 50
1795112673 50
1795112678 50
1795112683 50
1795112688 50
1795112693 50
1795112698 50
1795112703 50
1795112708 50
```
</details>

---

