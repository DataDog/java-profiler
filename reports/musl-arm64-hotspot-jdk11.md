---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 13:35:07 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
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
| CPU Samples | 390 |
| Sample Rate | 6.50/sec |
| Health Score | 406% |
| Threads | 11 |
| Allocations | 181 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 11 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (4 unique values: 39-47 cores)</summary>

```
1795631437 47
1795631442 47
1795631447 47
1795631452 47
1795631457 47
1795631462 47
1795631467 47
1795631472 47
1795631477 42
1795631482 42
1795631487 42
1795631492 42
1795631497 39
1795631502 39
1795631507 39
1795631512 39
1795631517 39
1795631522 39
1795631527 39
1795631532 39
```
</details>

---

