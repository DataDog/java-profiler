---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-20 12:15:12 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 12 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 176 |
| Sample Rate | 2.93/sec |
| Health Score | 183% |
| Threads | 11 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795194687 50
1795194692 50
1795194697 50
1795194702 50
1795194707 50
1795194712 50
1795194717 50
1795194722 50
1795194727 50
1795194732 50
1795194737 50
1795194742 50
1795194747 50
1795194752 50
1795194757 50
1795194762 50
1795194767 50
1795194772 50
1795194777 50
1795194782 50
```
</details>

---

