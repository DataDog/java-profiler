---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-03 11:12:38 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 496 |
| Sample Rate | 8.27/sec |
| Health Score | 517% |
| Threads | 8 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 829 |
| Sample Rate | 13.82/sec |
| Health Score | 864% |
| Threads | 11 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (2 unique values: 32-36 cores)</summary>

```
1770134693 32
1770134698 32
1770134703 32
1770134708 32
1770134713 32
1770134718 32
1770134723 32
1770134728 32
1770134733 32
1770134738 32
1770134743 32
1770134748 32
1770134753 32
1770134758 32
1770134763 32
1770134768 32
1770134773 32
1770134778 32
1770134783 32
1770134788 32
```
</details>

---

