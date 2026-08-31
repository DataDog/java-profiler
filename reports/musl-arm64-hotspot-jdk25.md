---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-31 11:44:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 11 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 177 |
| Sample Rate | 2.95/sec |
| Health Score | 184% |
| Threads | 12 |
| Allocations | 117 |

<details>
<summary>CPU Timeline (2 unique values: 60-62 cores)</summary>

```
1788190783 62
1788190788 62
1788190793 62
1788190798 62
1788190803 62
1788190808 62
1788190813 62
1788190818 62
1788190823 62
1788190828 62
1788190833 62
1788190838 62
1788190843 62
1788190848 60
1788190853 60
1788190858 60
1788190863 60
1788190868 60
1788190873 60
1788190878 60
```
</details>

---

