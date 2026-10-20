---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-20 10:08:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 479 |
| Sample Rate | 7.98/sec |
| Health Score | 499% |
| Threads | 8 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 796 |
| Sample Rate | 13.27/sec |
| Health Score | 829% |
| Threads | 10 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (5 unique values: 79-90 cores)</summary>

```
1792504985 79
1792504990 87
1792504995 87
1792505000 89
1792505005 89
1792505010 89
1792505015 89
1792505020 89
1792505025 89
1792505030 89
1792505035 89
1792505040 89
1792505045 87
1792505050 87
1792505055 87
1792505060 87
1792505065 87
1792505070 85
1792505075 85
1792505080 85
```
</details>

---

