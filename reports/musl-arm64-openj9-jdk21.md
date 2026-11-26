---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-26 06:15:16 EST

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 9 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 8 |
| Allocations | 20 |

<details>
<summary>CPU Timeline (2 unique values: 28-33 cores)</summary>

```
1795691098 33
1795691103 33
1795691108 33
1795691113 33
1795691118 33
1795691123 33
1795691128 28
1795691133 28
1795691138 28
1795691143 28
1795691149 28
1795691154 28
1795691159 28
1795691164 28
1795691169 28
1795691174 28
1795691179 28
1795691184 28
1795691189 28
1795691194 28
```
</details>

---

