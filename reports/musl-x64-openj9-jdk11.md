---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-13 05:46:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 8 |
| Allocations | 338 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 768 |
| Sample Rate | 12.80/sec |
| Health Score | 800% |
| Threads | 10 |
| Allocations | 540 |

<details>
<summary>CPU Timeline (2 unique values: 22-32 cores)</summary>

```
1786614120 22
1786614125 22
1786614130 22
1786614135 22
1786614140 22
1786614145 22
1786614150 22
1786614155 32
1786614160 32
1786614165 32
1786614170 32
1786614175 32
1786614180 32
1786614185 32
1786614190 32
1786614195 32
1786614200 32
1786614205 32
1786614210 32
1786614215 32
```
</details>

---

