---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-02 11:54:34 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 12 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 289 |
| Sample Rate | 4.82/sec |
| Health Score | 301% |
| Threads | 14 |
| Allocations | 147 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793638117 48
1793638122 48
1793638127 48
1793638132 48
1793638137 48
1793638142 48
1793638147 43
1793638152 43
1793638157 43
1793638162 43
1793638167 43
1793638172 43
1793638177 43
1793638182 43
1793638187 43
1793638192 43
1793638197 43
1793638202 43
1793638207 43
1793638212 43
```
</details>

---

