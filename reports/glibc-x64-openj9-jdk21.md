---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-02 11:02:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 770 |
| Sample Rate | 12.83/sec |
| Health Score | 802% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1018 |
| Sample Rate | 16.97/sec |
| Health Score | 1061% |
| Threads | 12 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (2 unique values: 60-63 cores)</summary>

```
1793635100 60
1793635105 60
1793635110 60
1793635115 60
1793635120 60
1793635125 60
1793635130 60
1793635135 60
1793635140 60
1793635145 60
1793635150 60
1793635155 60
1793635160 60
1793635165 63
1793635170 63
1793635175 63
1793635180 63
1793635185 63
1793635190 63
1793635195 63
```
</details>

---

