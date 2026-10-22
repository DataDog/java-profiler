---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-22 16:56:11 EDT

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 11 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 11 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (3 unique values: 45-57 cores)</summary>

```
1792702102 52
1792702107 52
1792702112 52
1792702117 52
1792702122 52
1792702127 52
1792702132 52
1792702137 52
1792702142 52
1792702147 52
1792702152 52
1792702157 52
1792702162 52
1792702167 52
1792702172 57
1792702177 57
1792702182 57
1792702187 57
1792702192 57
1792702197 57
```
</details>

---

