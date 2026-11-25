---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 13:35:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 11 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 11 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (3 unique values: 29-34 cores)</summary>

```
1795631486 30
1795631491 30
1795631496 30
1795631501 30
1795631506 30
1795631511 30
1795631516 30
1795631521 30
1795631526 30
1795631531 30
1795631536 30
1795631541 30
1795631546 34
1795631551 34
1795631556 34
1795631561 34
1795631566 29
1795631571 29
1795631576 29
1795631581 29
```
</details>

---

