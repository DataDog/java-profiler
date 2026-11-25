---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 13:35:07 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 8 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 774 |
| Sample Rate | 12.90/sec |
| Health Score | 806% |
| Threads | 12 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (4 unique values: 39-47 cores)</summary>

```
1795631434 47
1795631439 47
1795631444 47
1795631449 47
1795631454 47
1795631459 47
1795631464 47
1795631469 47
1795631474 42
1795631479 42
1795631484 42
1795631489 42
1795631494 39
1795631499 39
1795631504 39
1795631509 39
1795631514 39
1795631519 39
1795631524 39
1795631529 39
```
</details>

---

