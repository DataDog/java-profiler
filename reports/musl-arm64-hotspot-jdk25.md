---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-19 11:59:38 EDT

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 16 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1787154926 36
1787154931 36
1787154936 36
1787154941 36
1787154946 36
1787154951 36
1787154956 36
1787154961 36
1787154966 36
1787154971 36
1787154976 36
1787154981 36
1787154986 48
1787154991 48
1787154996 48
1787155001 48
1787155006 48
1787155011 48
1787155016 48
1787155021 48
```
</details>

---

