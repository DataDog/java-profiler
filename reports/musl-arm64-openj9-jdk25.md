---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-21 11:01:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 11 |
| Allocations | 81 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1787324179 64
1787324184 64
1787324189 64
1787324194 64
1787324199 64
1787324204 64
1787324209 64
1787324214 64
1787324219 64
1787324224 64
1787324229 64
1787324234 64
1787324239 64
1787324244 64
1787324249 64
1787324254 64
1787324259 64
1787324264 64
1787324269 64
1787324274 64
```
</details>

---

