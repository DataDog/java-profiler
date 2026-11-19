---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-19 09:12:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 10 |
| Allocations | 45 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 14 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795097271 50
1795097276 50
1795097281 50
1795097286 50
1795097291 50
1795097297 50
1795097302 50
1795097307 50
1795097312 50
1795097317 50
1795097322 50
1795097327 50
1795097332 50
1795097337 50
1795097342 50
1795097347 50
1795097352 50
1795097357 50
1795097362 50
1795097367 50
```
</details>

---

