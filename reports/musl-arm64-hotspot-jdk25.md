---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-30 05:49:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 368 |
| Sample Rate | 6.13/sec |
| Health Score | 383% |
| Threads | 8 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 11 |
| Allocations | 26 |

<details>
<summary>CPU Timeline (3 unique values: 15-18 cores)</summary>

```
1788083048 18
1788083053 18
1788083058 18
1788083063 16
1788083068 16
1788083073 15
1788083078 15
1788083083 15
1788083088 15
1788083093 15
1788083098 15
1788083103 15
1788083108 15
1788083113 18
1788083118 18
1788083123 18
1788083128 18
1788083133 18
1788083138 18
1788083143 18
```
</details>

---

