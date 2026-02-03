---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-03 11:11:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 645 |
| Sample Rate | 10.75/sec |
| Health Score | 672% |
| Threads | 11 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 779 |
| Sample Rate | 12.98/sec |
| Health Score | 811% |
| Threads | 12 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (3 unique values: 47-96 cores)</summary>

```
1770134698 47
1770134703 47
1770134708 47
1770134713 47
1770134718 47
1770134723 47
1770134728 79
1770134733 79
1770134738 79
1770134743 79
1770134748 96
1770134753 96
1770134758 96
1770134763 96
1770134768 96
1770134773 96
1770134778 96
1770134783 96
1770134788 96
1770134793 96
```
</details>

---

