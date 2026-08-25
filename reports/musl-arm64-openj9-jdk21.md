---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-25 11:03:31 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 10 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787669808 48
1787669813 48
1787669818 48
1787669823 48
1787669828 48
1787669833 48
1787669838 48
1787669843 48
1787669848 48
1787669853 48
1787669858 43
1787669863 43
1787669868 43
1787669873 43
1787669878 43
1787669883 43
1787669888 43
1787669894 43
1787669899 43
1787669904 43
```
</details>

---

