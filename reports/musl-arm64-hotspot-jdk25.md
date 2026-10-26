---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-26 14:59:56 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 251 |
| Sample Rate | 4.18/sec |
| Health Score | 261% |
| Threads | 11 |
| Allocations | 157 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793040908 48
1793040913 48
1793040918 48
1793040923 48
1793040928 48
1793040933 48
1793040938 48
1793040943 48
1793040948 48
1793040953 48
1793040958 48
1793040963 48
1793040968 48
1793040973 43
1793040978 43
1793040983 43
1793040988 43
1793040993 43
1793040998 43
1793041003 43
```
</details>

---

