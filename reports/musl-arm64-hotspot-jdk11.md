---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-05 00:55:42 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 675 |
| Sample Rate | 11.25/sec |
| Health Score | 703% |
| Threads | 8 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 417 |
| Sample Rate | 6.95/sec |
| Health Score | 434% |
| Threads | 14 |
| Allocations | 131 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1791175916 51
1791175921 51
1791175926 51
1791175931 51
1791175936 51
1791175941 51
1791175946 51
1791175951 64
1791175956 64
1791175961 64
1791175966 64
1791175971 64
1791175976 64
1791175981 64
1791175986 64
1791175991 64
1791175996 64
1791176001 64
1791176006 64
1791176011 64
```
</details>

---

