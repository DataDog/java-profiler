---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-30 06:28:17 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 123 |
| Sample Rate | 2.05/sec |
| Health Score | 128% |
| Threads | 12 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1056 |
| Sample Rate | 17.60/sec |
| Health Score | 1100% |
| Threads | 9 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1793355805 40
1793355810 40
1793355815 40
1793355820 40
1793355825 40
1793355830 40
1793355835 40
1793355840 40
1793355845 40
1793355850 40
1793355855 40
1793355860 40
1793355865 40
1793355870 40
1793355875 40
1793355880 40
1793355885 40
1793355890 40
1793355895 40
1793355900 40
```
</details>

---

