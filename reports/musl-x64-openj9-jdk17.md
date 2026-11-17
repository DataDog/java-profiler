---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-17 10:58:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 338 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 682 |
| Sample Rate | 11.37/sec |
| Health Score | 711% |
| Threads | 11 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (4 unique values: 70-79 cores)</summary>

```
1794930672 77
1794930677 79
1794930682 79
1794930687 79
1794930692 79
1794930697 79
1794930702 79
1794930707 79
1794930712 79
1794930717 79
1794930722 79
1794930727 74
1794930732 74
1794930737 74
1794930742 70
1794930747 70
1794930752 70
1794930757 70
1794930762 70
1794930767 70
```
</details>

---

