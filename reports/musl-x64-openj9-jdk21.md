---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 13:36:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 722 |
| Sample Rate | 12.03/sec |
| Health Score | 752% |
| Threads | 11 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (7 unique values: 54-78 cores)</summary>

```
1795631445 54
1795631450 54
1795631455 54
1795631460 54
1795631465 54
1795631470 63
1795631475 63
1795631480 68
1795631485 68
1795631490 68
1795631495 65
1795631500 65
1795631505 74
1795631510 74
1795631515 74
1795631520 74
1795631525 74
1795631530 74
1795631535 76
1795631540 76
```
</details>

---

