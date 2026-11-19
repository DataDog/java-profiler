---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-19 13:36:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 232 |
| Sample Rate | 3.87/sec |
| Health Score | 242% |
| Threads | 14 |
| Allocations | 139 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795113167 50
1795113172 50
1795113177 50
1795113182 50
1795113187 50
1795113192 50
1795113197 50
1795113202 50
1795113207 50
1795113212 50
1795113217 50
1795113222 50
1795113227 50
1795113232 50
1795113237 50
1795113242 50
1795113247 50
1795113252 50
1795113257 50
1795113262 50
```
</details>

---

