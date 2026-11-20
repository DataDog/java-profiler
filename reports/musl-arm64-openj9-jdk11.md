---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-20 11:32:48 EST

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
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 11 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 125 |
| Sample Rate | 2.08/sec |
| Health Score | 130% |
| Threads | 14 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795192082 64
1795192087 64
1795192092 64
1795192097 64
1795192102 64
1795192107 64
1795192112 64
1795192117 64
1795192122 64
1795192127 64
1795192132 64
1795192137 64
1795192142 64
1795192147 64
1795192152 64
1795192157 64
1795192162 64
1795192167 64
1795192172 64
1795192177 64
```
</details>

---

