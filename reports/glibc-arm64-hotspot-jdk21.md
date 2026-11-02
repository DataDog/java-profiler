---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-02 11:54:31 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 149 |
| Sample Rate | 2.48/sec |
| Health Score | 155% |
| Threads | 8 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 10 |
| Allocations | 78 |

<details>
<summary>CPU Timeline (2 unique values: 53-64 cores)</summary>

```
1793638137 64
1793638142 64
1793638147 64
1793638152 53
1793638157 53
1793638162 53
1793638167 53
1793638172 53
1793638177 53
1793638182 53
1793638187 53
1793638192 53
1793638197 53
1793638202 53
1793638207 53
1793638212 53
1793638217 53
1793638222 53
1793638227 53
1793638232 53
```
</details>

---

