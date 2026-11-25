---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 13:36:20 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 11 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795631462 64
1795631467 64
1795631472 64
1795631477 64
1795631482 64
1795631487 64
1795631492 64
1795631497 64
1795631502 64
1795631507 64
1795631512 64
1795631517 64
1795631522 64
1795631527 64
1795631532 64
1795631537 64
1795631542 64
1795631547 64
1795631552 64
1795631557 64
```
</details>

---

