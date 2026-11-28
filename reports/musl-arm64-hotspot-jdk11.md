---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-28 00:04:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 32 |
| Sample Rate | 0.53/sec |
| Health Score | 33% |
| Threads | 11 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (2 unique values: 33-40 cores)</summary>

```
1795842063 40
1795842068 40
1795842073 40
1795842078 40
1795842083 40
1795842088 40
1795842093 40
1795842098 40
1795842103 40
1795842108 40
1795842113 40
1795842118 40
1795842123 40
1795842128 40
1795842133 40
1795842138 40
1795842143 40
1795842148 40
1795842153 40
1795842158 40
```
</details>

---

