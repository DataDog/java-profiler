---
layout: default
title: musl-arm64-openj9-jdk8
---

## musl-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-30 08:24:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 30-48 cores)</summary>

```
1790770751 30
1790770756 30
1790770761 30
1790770766 30
1790770771 39
1790770776 39
1790770781 39
1790770786 48
1790770791 48
1790770796 48
1790770801 48
1790770806 48
1790770811 48
1790770816 48
1790770821 48
1790770826 48
1790770831 48
1790770836 48
1790770841 48
1790770846 48
```
</details>

---

