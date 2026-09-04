---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-04 05:50:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 673 |
| Sample Rate | 11.22/sec |
| Health Score | 701% |
| Threads | 10 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (3 unique values: 92-96 cores)</summary>

```
1788515185 96
1788515190 94
1788515195 94
1788515200 94
1788515205 94
1788515210 92
1788515215 92
1788515220 92
1788515225 94
1788515230 94
1788515235 94
1788515240 94
1788515245 94
1788515250 94
1788515255 96
1788515260 96
1788515265 96
1788515270 96
1788515275 96
1788515280 96
```
</details>

---

