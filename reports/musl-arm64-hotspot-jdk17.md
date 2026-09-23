---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-23 05:40:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 12 |
| Allocations | 23 |

<details>
<summary>CPU Timeline (3 unique values: 37-46 cores)</summary>

```
1790156096 46
1790156101 46
1790156106 46
1790156111 46
1790156116 46
1790156121 46
1790156126 46
1790156131 37
1790156136 37
1790156141 37
1790156146 37
1790156151 37
1790156156 39
1790156161 39
1790156166 39
1790156171 39
1790156176 39
1790156181 39
1790156186 39
1790156191 39
```
</details>

---

