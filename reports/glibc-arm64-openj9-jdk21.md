---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-15 05:56:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
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
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 8 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 208 |
| Sample Rate | 3.47/sec |
| Health Score | 217% |
| Threads | 12 |
| Allocations | 152 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1794739944 40
1794739949 40
1794739954 40
1794739959 40
1794739964 40
1794739969 40
1794739974 40
1794739979 40
1794739984 40
1794739989 40
1794739994 40
1794739999 40
1794740004 40
1794740009 40
1794740014 40
1794740019 40
1794740024 40
1794740029 40
1794740034 40
1794740039 40
```
</details>

---

