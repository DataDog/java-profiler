---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 12:28:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 513 |
| Sample Rate | 8.55/sec |
| Health Score | 534% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 813 |
| Sample Rate | 13.55/sec |
| Health Score | 847% |
| Threads | 11 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (3 unique values: 57-66 cores)</summary>

```
1795627373 65
1795627378 65
1795627383 65
1795627388 65
1795627393 65
1795627398 65
1795627403 65
1795627408 65
1795627413 66
1795627418 66
1795627423 66
1795627428 66
1795627433 66
1795627439 66
1795627444 57
1795627449 57
1795627454 57
1795627459 57
1795627464 57
1795627469 57
```
</details>

---

