---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-02 07:03:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 12 |
| Allocations | 36 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 170 |
| Sample Rate | 2.83/sec |
| Health Score | 177% |
| Threads | 11 |
| Allocations | 130 |

<details>
<summary>CPU Timeline (3 unique values: 35-40 cores)</summary>

```
1793620790 35
1793620795 35
1793620800 40
1793620805 40
1793620810 40
1793620815 40
1793620820 40
1793620825 40
1793620830 40
1793620835 40
1793620840 40
1793620845 40
1793620850 40
1793620855 40
1793620860 40
1793620865 40
1793620870 39
1793620875 39
1793620880 39
1793620885 39
```
</details>

---

