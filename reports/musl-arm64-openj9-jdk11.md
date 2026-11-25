---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 13:35:07 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 353 |
| Sample Rate | 5.88/sec |
| Health Score | 368% |
| Threads | 9 |
| Allocations | 204 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 118 |
| Sample Rate | 1.97/sec |
| Health Score | 123% |
| Threads | 13 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (3 unique values: 28-59 cores)</summary>

```
1795631430 33
1795631435 33
1795631440 33
1795631445 33
1795631450 33
1795631455 33
1795631460 33
1795631465 33
1795631470 28
1795631475 28
1795631480 28
1795631485 28
1795631490 28
1795631495 28
1795631500 28
1795631505 28
1795631510 59
1795631515 59
1795631520 59
1795631525 59
```
</details>

---

