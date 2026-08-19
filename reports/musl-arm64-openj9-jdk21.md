---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-19 06:13:37 EDT

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
| CPU Samples | 319 |
| Sample Rate | 5.32/sec |
| Health Score | 332% |
| Threads | 11 |
| Allocations | 154 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 13 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787134012 48
1787134017 48
1787134022 48
1787134027 48
1787134032 48
1787134037 48
1787134042 48
1787134047 48
1787134052 48
1787134057 48
1787134062 48
1787134067 43
1787134072 43
1787134077 43
1787134082 43
1787134087 43
1787134092 43
1787134097 43
1787134102 43
1787134107 43
```
</details>

---

