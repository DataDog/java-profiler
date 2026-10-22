---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-22 12:29:06 EDT

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 649 |
| Sample Rate | 10.82/sec |
| Health Score | 676% |
| Threads | 8 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 790 |
| Sample Rate | 13.17/sec |
| Health Score | 823% |
| Threads | 10 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1792686131 94
1792686136 94
1792686141 94
1792686146 96
1792686151 96
1792686156 96
1792686161 96
1792686166 96
1792686171 96
1792686176 96
1792686181 96
1792686186 96
1792686191 96
1792686196 96
1792686201 96
1792686206 96
1792686211 96
1792686216 96
1792686221 96
1792686226 96
```
</details>

---

