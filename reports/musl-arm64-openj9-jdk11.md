---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-18 15:28:27 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 10 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 12 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787080929 64
1787080934 64
1787080939 64
1787080944 64
1787080949 64
1787080954 64
1787080959 64
1787080964 64
1787080969 64
1787080974 64
1787080979 64
1787080984 64
1787080989 64
1787080994 64
1787080999 64
1787081004 64
1787081009 64
1787081014 64
1787081019 64
1787081024 64
```
</details>

---

