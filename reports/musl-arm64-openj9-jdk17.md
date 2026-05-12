---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-12 04:02:15 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 138 |
| Sample Rate | 2.30/sec |
| Health Score | 144% |
| Threads | 10 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (2 unique values: 51-56 cores)</summary>

```
1778572526 51
1778572531 51
1778572536 51
1778572541 51
1778572546 51
1778572551 51
1778572556 51
1778572561 51
1778572566 51
1778572571 51
1778572576 51
1778572581 51
1778572586 51
1778572591 51
1778572596 51
1778572601 51
1778572606 51
1778572611 51
1778572616 51
1778572621 51
```
</details>

---

