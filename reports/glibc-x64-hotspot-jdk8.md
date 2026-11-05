---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-05 09:56:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 191 |
| Sample Rate | 3.18/sec |
| Health Score | 199% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 444 |
| Sample Rate | 7.40/sec |
| Health Score | 462% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 66-81 cores)</summary>

```
1793890196 79
1793890201 79
1793890206 79
1793890211 79
1793890216 79
1793890221 79
1793890226 79
1793890231 79
1793890236 79
1793890241 81
1793890246 81
1793890251 81
1793890256 81
1793890261 81
1793890266 79
1793890271 79
1793890276 77
1793890281 77
1793890286 77
1793890291 77
```
</details>

---

