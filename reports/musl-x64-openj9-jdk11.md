---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 13:18:19 EST

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 740 |
| Sample Rate | 12.33/sec |
| Health Score | 771% |
| Threads | 10 |
| Allocations | 334 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 868 |
| Sample Rate | 14.47/sec |
| Health Score | 904% |
| Threads | 11 |
| Allocations | 551 |

<details>
<summary>CPU Timeline (2 unique values: 89-96 cores)</summary>

```
1794420791 89
1794420796 89
1794420801 89
1794420806 89
1794420811 89
1794420816 89
1794420821 89
1794420827 89
1794420832 89
1794420837 89
1794420842 96
1794420847 96
1794420852 96
1794420857 96
1794420862 96
1794420867 96
1794420872 96
1794420877 96
1794420882 96
1794420887 96
```
</details>

---

