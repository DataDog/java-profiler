---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-22 11:52:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 579 |
| Sample Rate | 9.65/sec |
| Health Score | 603% |
| Threads | 8 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 818 |
| Sample Rate | 13.63/sec |
| Health Score | 852% |
| Threads | 10 |
| Allocations | 555 |

<details>
<summary>CPU Timeline (2 unique values: 74-76 cores)</summary>

```
1790091823 74
1790091828 74
1790091833 74
1790091838 76
1790091843 76
1790091848 76
1790091853 76
1790091858 76
1790091863 76
1790091868 76
1790091873 76
1790091878 76
1790091883 76
1790091888 76
1790091893 76
1790091898 76
1790091903 76
1790091908 76
1790091913 76
1790091918 76
```
</details>

---

