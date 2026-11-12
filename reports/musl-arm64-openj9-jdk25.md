---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-12 09:02:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 114 |
| Sample Rate | 1.90/sec |
| Health Score | 119% |
| Threads | 10 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1794491703 48
1794491708 48
1794491713 48
1794491718 48
1794491723 48
1794491728 48
1794491733 48
1794491738 48
1794491743 48
1794491748 48
1794491753 48
1794491758 48
1794491763 48
1794491768 48
1794491773 48
1794491778 48
1794491783 48
1794491788 43
1794491793 43
1794491798 43
```
</details>

---

