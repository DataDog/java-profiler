---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-19 13:19:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 444 |
| Sample Rate | 7.40/sec |
| Health Score | 462% |
| Threads | 9 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 893 |
| Sample Rate | 14.88/sec |
| Health Score | 930% |
| Threads | 11 |
| Allocations | 445 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1787159761 96
1787159766 96
1787159771 96
1787159776 96
1787159781 96
1787159786 96
1787159791 96
1787159796 96
1787159801 96
1787159806 94
1787159811 94
1787159816 94
1787159821 94
1787159826 94
1787159831 94
1787159836 94
1787159841 94
1787159846 94
1787159851 94
1787159856 94
```
</details>

---

