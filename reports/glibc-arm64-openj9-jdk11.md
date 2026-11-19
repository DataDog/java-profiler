---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 09:12:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 11 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 392 |
| Sample Rate | 6.53/sec |
| Health Score | 408% |
| Threads | 13 |
| Allocations | 164 |

<details>
<summary>CPU Timeline (3 unique values: 32-44 cores)</summary>

```
1795097297 40
1795097302 40
1795097307 40
1795097312 40
1795097317 40
1795097322 40
1795097327 40
1795097332 40
1795097337 40
1795097342 40
1795097347 40
1795097352 40
1795097357 40
1795097362 40
1795097367 40
1795097372 40
1795097377 40
1795097382 44
1795097387 44
1795097392 44
```
</details>

---

