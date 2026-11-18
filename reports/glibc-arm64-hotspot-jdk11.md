---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 07:34:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 975 |
| Sample Rate | 16.25/sec |
| Health Score | 1016% |
| Threads | 9 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (3 unique values: 32-39 cores)</summary>

```
1795005053 39
1795005058 39
1795005063 39
1795005068 39
1795005073 39
1795005078 39
1795005083 39
1795005088 39
1795005093 39
1795005098 39
1795005103 39
1795005108 39
1795005113 39
1795005118 39
1795005123 39
1795005128 34
1795005133 34
1795005138 34
1795005143 34
1795005148 34
```
</details>

---

