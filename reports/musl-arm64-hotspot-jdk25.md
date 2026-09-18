---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 11:10:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 9 |
| Allocations | 20 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1789743395 38
1789743400 38
1789743405 38
1789743410 38
1789743415 38
1789743420 38
1789743425 38
1789743430 38
1789743435 38
1789743440 43
1789743445 43
1789743450 43
1789743455 43
1789743460 43
1789743465 43
1789743470 43
1789743475 43
1789743480 43
1789743485 43
1789743490 43
```
</details>

---

