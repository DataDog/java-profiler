---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-11 11:48:07 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 8 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 305 |
| Sample Rate | 5.08/sec |
| Health Score | 318% |
| Threads | 11 |
| Allocations | 171 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1786462988 32
1786462993 32
1786462998 32
1786463003 32
1786463008 32
1786463013 32
1786463018 32
1786463023 32
1786463028 32
1786463033 32
1786463038 32
1786463043 32
1786463048 32
1786463053 32
1786463059 32
1786463064 32
1786463069 32
1786463074 32
1786463079 32
1786463084 32
```
</details>

---

