---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-30 08:37:25 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 10 |
| Allocations | 44 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 250 |
| Sample Rate | 4.17/sec |
| Health Score | 261% |
| Threads | 12 |
| Allocations | 133 |

<details>
<summary>CPU Timeline (3 unique values: 40-48 cores)</summary>

```
1790771561 48
1790771566 48
1790771572 48
1790771577 48
1790771582 40
1790771587 40
1790771592 40
1790771597 40
1790771602 40
1790771607 40
1790771612 40
1790771617 40
1790771622 40
1790771627 40
1790771632 40
1790771637 40
1790771642 45
1790771647 45
1790771652 45
1790771657 45
```
</details>

---

